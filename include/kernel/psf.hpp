#pragma once

#include "common.hpp"
#include "common_k.hpp"
#include "util.hpp"

typedef char PsfSymbol;

// information for each psf file
// these values are available in only runtime
extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_start;
extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_end;
extern PsfSymbol _binary_resources_CyrKoi_Terminus32x16_psf_size;

extern PsfSymbol _binary_resources_CyrKoi_Terminus16_psf_start;
extern PsfSymbol _binary_resources_CyrKoi_Terminus16_psf_end;
extern PsfSymbol _binary_resources_CyrKoi_Terminus16_psf_size;

// psf header 
enum class PsfVersion {
    Version1,
    Version2
};

const uint8_t psf1_magic[2] = {0x36, 0x04};
const uint8_t psf1_mode512 = 0x01;
const uint8_t psf1_modehastab = 0x02;
const uint8_t psf1_modehasseq = 0x04;

struct Psf1Header {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t charsize;
};

struct Psf2Header {
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
        uint32_t bytes_perglyph;
        uint64_t datasize;
        void *glyphs_startaddr;
        uint32_t getGlyphIndex(uint32_t c);
    public:
        PsfFont(PsfVersion version, PsfSymbol& start, PsfSymbol& end, PsfSymbol& size);
        uint32_t height;
        uint32_t width;
        uint8_t* getGlyphaddr(uint32_t index);
        void getLine(uint32_t c, uint32_t height, uint8_t line[]);
        static void test();
};

