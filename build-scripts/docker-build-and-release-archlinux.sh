#! /bin/bash -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source $DIR/common-vars

BUILD_DATE="dev"

if [[ "$TRAVIS" == "true" ]]; then
  BUILD_DATE=$(date -u +%s)
  echo "$DOCKER_PASSWORD" | docker login -u "$DOCKER_USERNAME" --password-stdin
fi

docker build \
  -t cgspeck/barndoor-tracker:latest \
  --build-arg BUILD_DATE \
  --build-arg VERSION=$ARCH_VERSION \
  .

IMG_NAME="cgspeck/barndoor-tracker:${TRAVIS_BUILD_NUMBER}"
echo "Creating Docker Tag: ${IMG_NAME}"
docker tag cgspeck/barndoor-tracker:latest $IMG_NAME

if [[ "$TRAVIS" == "true" && "$BRANCH_NAME" == "develop" ]]; then
  echo -e "\nPushing new docker image: cgspeck/barndoor-tracker:latest"
  docker push cgspeck/barndoor-tracker:latest
  echo -e "\nPushing new docker image: $IMG_NAME"
  docker push $IMG_NAME
fi
