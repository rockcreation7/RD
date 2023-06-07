FROM rust:1.67 as builder
WORKDIR /usr/src/tool001
COPY . .
RUN cargo install --path .

FROM debian:bullseye-slim
RUN apt-get update && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/cargo/bin/tool001 /usr/local/bin/tool001
CMD ["tool001"]