FROM archlinux/base
ARG BUILD_DATE
ARG VERSION
LABEL build_version="Barndoor Tracker Archlinux Devel version:- ${VERSION} Build-date:- ${BUILD_DATE}"

ENV TZ=Australia/Melbourne
WORKDIR /app

RUN pacman -Sy && pacman -S -y --noconfirm --needed \
    cmake \
    base-devel \
    go \
    git \
    neovim \
    nodejs \
    npm \
    arduino-avr-core \
    esptool

ADD ./ /app/barndoor-tracker
RUN git clone https://aur.archlinux.org/yay.git

RUN useradd -m abc
RUN echo 'abc ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers
RUN chown -R abc:abc /app

USER abc

WORKDIR /app/yay
RUN makepkg -si --noconfirm
RUN yay -Sy && yay -S -y --noconfirm --needed \
    arduino-mk

WORKDIR /app/barndoor-tracker/esp32/tools
RUN python get.py

RUN echo "Build the demo app..."
WORKDIR /app/barndoor-tracker/makeEspArduino
RUN make -f makeEspArduino.mk ESP_ROOT=/app/barndoor-tracker/esp32 CHIP=esp32 DEMO=1

RUN echo "Buid the frontend..."
WORKDIR /app/barndoor-tracker/frontend
RUN npm i
RUN npm run test
RUN npm run docker:build

RUN echo "Front-end build size"
# WORKDIR /app/barndoor-tracker
# RUN du -hs src/data

WORKDIR /app/barndoor-tracker
CMD make
