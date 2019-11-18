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

WORKDIR /app/barndoor-tracker
CMD /app/barndoor-tracker/build-scripts/build.sh