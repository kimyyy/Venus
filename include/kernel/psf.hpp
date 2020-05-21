#pragma once

#include "common.hpp"

typedef char PsfSymbol;

extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_start;
extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_end;
extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_size;

struct Psf2Header {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t charsize;
};

struct PSF2_Header {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
};

class PsfFont {
    private:
    bool hasUnicodeTable;
    uint32_t num_glyph;
    uint64_t datasize;
    public:
    uint32_t bytes_perglyph;
    void *bitmap_startaddr;
    uint32_t height;
    uint32_t width;
    PsfFont(uint8_t version, PsfSymbol& start, PsfSymbol& end, PsfSymbol& size);
    void* getGlyphaddr(uint32_t offset);
};

