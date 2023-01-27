## About The Project
This is a torrent client that allows you to interact through the telegram api.

Environmental requirements
---------------------
* CMake
* GCC / Clang
* Conan
* transmission-cli

Build
---------------------
```
git clone https://github.com/Ctulh/RemoteTorrentClient.git
cd RemoteTorrentClient
mkdir build && cd build
conan install .. --build=missing
cmake ..
cmake --build .
```
Setup configs
---------------------
There are two config files in [config](https://github.com/Ctulh/RemoteTorrentClient/tree/main/config) directory. 

* [torrentConfig.json](https://github.com/Ctulh/RemoteTorrentClient/blob/main/config/torrentConfig.json) - config for the transmission-cli.

  | Field | Description |
  | ------| -----------|
  | downloadDirectory | Directory where torrents will be downloaded. Directory should exist.
  
* [telegramConfig.json](https://github.com/Ctulh/RemoteTorrentClient/blob/main/config/telegramConfig.json) - config for the transmission-cli 

  | Field                        | Description          |
  | -----------------------------| ---------------------|
  | botToken                     | A unique authentication token. Token [creation](https://core.telegram.org/bots/features#botfather).
  | chatFilesDownloadDestination | Directory path for temporary files that bot accepts. By near the executable in `tgDownloads/` near the executable.
  
Interaction
--------------------- 
 Client supports three commands 
 - /add "torrent magnet link" (without quotes) - Starts downloading torrent.
 - /del "torrent id" (without quotes) - Deletes torrent.
 - /list - Prints the list with existing torrents and some statuses about them.
 
 ### Also client support attachable files. You can drag&drop or attach the torrent file to add it to the downloads.
  
