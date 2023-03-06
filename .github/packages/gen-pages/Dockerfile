FROM ubuntu:latest AS gen-pages
COPY .github/packages/gen-pages/setup.sh /usr/local/bin
COPY requirements.txt /tmp/
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C
RUN chmod +x /usr/local/bin/setup.sh && setup.sh
VOLUME [ "/input", "/output" ]
COPY .github/packages/gen-pages/entrypoint.sh /usr/local/bin
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT entrypoint.sh
