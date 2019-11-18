#! /bin/bash -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source $DIR/common-vars

BUILD_DATE="dev"

if [[ "$TRAVIS" == "true" ]]; then
  BUILD_DATE=$(date -u +%s)
  echo "$DOCKER_PASSWORD" | docker login -u "$DOCKER_USERNAME" --password-stdin
fi

IMG_NAME="cgspeck/barndoor-tracker:${TRAVIS_BUILD_NUMBER}"
echo "Pulling image"
docker pull $IMG_NAME
echo "Running container"
docker run \
  -it \
  --rm \
  $IMG_NAME
