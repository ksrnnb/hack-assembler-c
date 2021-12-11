FROM ubuntu:16.04

RUN apt-get update && apt-get -y install \
    bash \
    binutils \
    build-essential \
    coreutils \
    curl \
    grep \
    iproute2 \
    iputils-ping \
    iptables \
    isc-dhcp-client \
    man \
    procps \
    python3 \
    strace \
    tcpdump \
    traceroute \
    vim \
    wget

RUN apt-get install -y sysstat
WORKDIR /var/workspace/