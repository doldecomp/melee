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
