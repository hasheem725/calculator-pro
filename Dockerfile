# --- STAGE 1: Build ---
FROM ubuntu:22.04 AS builder
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y build-essential cmake && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && make

# --- STAGE 2: Runtime ---
FROM ubuntu:22.04
WORKDIR /root/

# Only copy the final application and the test binary for Jenkins to use
COPY --from=builder /app/build/calculator_app .
COPY --from=builder /app/build/unit_tests .

CMD ["./calculator_app"]
