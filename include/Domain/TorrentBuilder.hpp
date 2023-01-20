
#pragma once

#include "GenericTorrentBuilder.hpp"

class TorrentBuilder final : public GenericTorrentBuilder<TorrentBuilder> {
    using GenericTorrentBuilder<TorrentBuilder>::GenericTorrentBuilder;
};