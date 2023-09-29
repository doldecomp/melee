FROM ubuntu:latest AS build-linux
ARG WIBO_PATH="/usr/local/sbin/wibo"
COPY --from=ghcr.io/decompals/wibo:latest \
    ${WIBO_PATH} \
    ${WIBO_PATH}
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
VOLUME [ "/input", "/output" ]
ENV WINE=${WIBO_PATH}
ENV DEVKITPRO=${DEVKITPRO}
ENV DEVKITPPC=${DEVKITPPC}
ENV PATH="$DEVKITPRO/tools/bin:$PATH"
ENV PATH="$DEVKITPPC/bin:$PATH"
ENV MAKE_FLAGS="GENERATE_MAP=1"
COPY .github/packages/build-linux/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT entrypoint.sh
