FROM rust:latest as build-rust
RUN git clone 'https://github.com/InusualZ/dadosod.git' \
    && cd dadosod \
    && cargo build -r

FROM ubuntu:latest AS linux-base
ARG WIBO_PATH="/usr/local/sbin/wibo"
COPY --from=ghcr.io/decompals/wibo:latest \
    ${WIBO_PATH} \
    ${WIBO_PATH}
COPY requirements.txt /tmp/
COPY --from=build-rust \
     /dadosod/target/release/dadosod \
     /usr/local/bin/dadosod
ARG DEVKITPRO=/opt/devkitpro
ARG DEVKITPPC=${DEVKITPRO}/devkitPPC
COPY --from=devkitpro/devkitppc:latest  \
    ${DEVKITPPC}/bin/powerpc-eabi-as \
    ${DEVKITPPC}/bin/powerpc-eabi-as
COPY .github/packages/build-linux/setup.sh /usr/local/bin
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C
ENV MELEE_COMPILERS_URL="https://mega.nz/file/BU43wKxT#rVC11Rl7DPxfSn7V9Iu--8E7m7gc1gsJWtfVBbfmKwQ"
RUN chmod +x /usr/local/bin/setup.sh && setup.sh
ENV WINE=${WIBO_PATH}
ENV DEVKITPRO=${DEVKITPRO}
ENV DEVKITPPC=${DEVKITPPC}
ENV PATH="$DEVKITPRO/tools/bin:$PATH"
ENV PATH="$DEVKITPPC/bin:$PATH"
COPY .github/packages/build-linux/melee-mwcc /usr/local/bin
RUN chmod +x /usr/local/bin/melee-mwcc

FROM linux-base AS build-linux
ENV MAKE_FLAGS="GENERATE_MAP=1"
VOLUME [ "/input", "/output" ]
COPY .github/packages/build-linux/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT entrypoint.sh

FROM linux-base AS gen-pages
VOLUME [ "/input", "/output" ]
COPY .github/packages/gen-pages/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT entrypoint.sh

FROM linux-base AS dump-asm
ARG SHORT_SHA
ARG TREE_URL
VOLUME [ "/input", "/output" ]
COPY .github/packages/dump-asm/readme.py /usr/local/bin
RUN chmod +x /usr/local/bin/readme.py
COPY .github/packages/dump-asm/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENV SHORT_SHA="${SHORT_SHA}"
ENV TREE_URL="${TREE_URL}"
ENTRYPOINT entrypoint.sh

# TODO
FROM rust:latest AS check-issues
COPY .github/packages/check-issues/setup.sh /usr/local/bin
COPY . /input
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C
RUN chmod +x /usr/local/bin/setup.sh && setup.sh
RUN rm -rf /input
VOLUME [ "/input" ]
COPY .github/packages/check-issues/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT entrypoint.sh
