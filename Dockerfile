FROM galeksandrp/metamod-source:docker-master
RUN apt-get update
RUN apt-get install -y git
COPY .git /root/sourcemod/.git
WORKDIR /root/sourcemod
COPY product.version product.version
RUN git fetch --unshallow origin HEAD
RUN git remote add upstream https://github.com/alliedmodders/sourcemod.git
RUN git fetch upstream master
RUN wget $(echo "https://sm.alliedmods.net/smdrop/$(cat product.version | grep -o '[0-9]*\.[0-9]*' | head -1)/sourcemod-$(cat product.version)-git$(git rev-list --count $(git merge-base upstream/master HEAD))-linux.tar.gz") -O - | tar xz -C ~/css/cstrike
WORKDIR /root/css
