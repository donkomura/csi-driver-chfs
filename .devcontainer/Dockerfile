FROM mcr.microsoft.com/devcontainers/cpp:ubuntu

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# Update and upgrade repo
RUN apt-get update -y -q \
    && apt-get install -y wget git

# download and install golang
ENV GOVERSION=1.21.5
ENV GOPATH /go
RUN wget -P /tmp "https://go.dev/dl/go${GOVERSION}.linux-amd64.tar.gz" \
    && tar -C /usr/local -xzf /tmp/go${GOVERSION}.linux-amd64.tar.gz
RUN rm /tmp/go${GOVERSION}.linux-amd64.tar.gz
ENV PATH $GOPATH/bin:/usr/local/go/bin:$PATH
RUN mkdir -p "$GOPATH/src" "$GOPATH/bin" && chmod -R 777 "$GOPATH"

# install csi-sanity (v5)
RUN go install -v github.com/kubernetes-csi/csi-test/v5/cmd/csi-sanity@latest

# install chfs dependencies
RUN apt-get -y install \
    gcc automake \
    libtool pkgconf \
    python3 bison fuse sudo curl \
    libfuse-dev pandoc \
    libopenmpi-dev libssl-dev \
    gdb numactl

