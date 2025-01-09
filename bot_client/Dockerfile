FROM ghcr.io/joshuachen6/free-threaded-jit-python-docker-image:main

WORKDIR /pacbot/bot_client
COPY . .

RUN python3 -m pip install -r requirements.txt
ENTRYPOINT ["python3", "defaultClient.py"]
