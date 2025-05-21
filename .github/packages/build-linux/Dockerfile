FROM ubuntu:latest AS linux-base
ARG WIBO_PATH="/usr/local/sbin/wibo"
COPY --from=ghcr.io/decompals/wibo:0.6.11 \
    ${WIBO_PATH} \
    ${WIBO_PATH}
ARG DEVKITPRO=/opt/devkitpro
ARG DEVKITPPC=${DEVKITPRO}/devkitPPC
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C
ENV MELEE_COMPILERS_URL='https://files.decomp.dev/compilers_20250520.zip'
ENV BINUTILS_URL='https://github.com/encounter/gc-wii-binutils/releases/download/2.42-1/linux-x86_64.zip'
ENV WINE=${WIBO_PATH}
ENV DEVKITPRO=${DEVKITPRO}
ENV DEVKITPPC=${DEVKITPPC}
ENV PATH="$DEVKITPRO/tools/bin:$PATH"
ENV PATH="$DEVKITPPC/bin:$PATH"
COPY .github/packages/build-linux/melee-mwcc /usr/local/bin

FROM linux-base AS linux-rw
VOLUME ["/input", "/output"]

FROM linux-rw AS build-linux
COPY .github/packages/build-linux/setup.sh /usr/local/bin
RUN setup.sh
ENV MAKE_FLAGS="GENERATE_MAP=1"
COPY .github/packages/build-linux/entrypoint.sh /usr/local/bin
ENTRYPOINT ["entrypoint.sh"]

FROM linux-rw AS gen-pages
COPY .github/packages/gen-pages/setup.sh /usr/local/bin
COPY /reqs/gen-pages.txt /tmp/reqs/
RUN setup.sh
COPY .github/packages/gen-pages/entrypoint.sh /usr/local/bin
ENTRYPOINT ["entrypoint.sh"]

# TODO
FROM rust:latest AS check-issues
COPY .github/packages/check-issues/setup.sh /usr/local/bin
COPY . /input
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C
RUN setup.sh
RUN rm -rf /input
VOLUME [ "/input" ]
COPY .github/packages/check-issues/entrypoint.sh /usr/local/bin
ENTRYPOINT ["entrypoint.sh"]
