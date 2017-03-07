FROM galeksandrp/metamod-source:docker-1.10-dev-user
USER root
RUN apt-get update && apt-get install -y git
WORKDIR /home/css/sourcemod
COPY .git .git
COPY product.version product.version
RUN chown -R css:css .
USER css
RUN git fetch --unshallow origin HEAD
RUN git remote add upstream https://github.com/alliedmodders/sourcemod.git
RUN git fetch upstream $(cat product.version | grep -o '[0-9]*\.[0-9]*' | head -1)-dev
RUN wget $(echo "https://sm.alliedmods.net/smdrop/$(cat product.version | grep -o '[0-9]*\.[0-9]*' | head -1)/sourcemod-$(cat product.version)-git$(git rev-list --count $(git merge-base upstream/$(cat product.version | grep -o '[0-9]*\.[0-9]*' | head -1)-dev HEAD))-linux.tar.gz") -O - | tar xz -C ~/css/cstrike
WORKDIR /home/css/css
