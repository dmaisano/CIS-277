# #!/bin/bash

if [ ! -f ./netflix.json ]; then
  wget https://www.reddit.com/r/NetflixBestOf.json -O netflix.json
fi

# grep -E '"data": {(.+?)}}' netflix.json
