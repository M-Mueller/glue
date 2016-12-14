#include "glue/GlTexture2D.h"
#include "glue/GlInternal.h"

#include <png.h>
#include <cstdio>

#define PNGSIGSIZE 8

GlTexture2D::GlTexture2D():
    _width(0),
    _height(0)
{

}

GlTexture::Type GlTexture2D::type() const
{
    return Type::Texture2D;
}

void GlTexture2D::setImageData(GlTexture::InternalFormat format, int width, int height, GlTexture::PixelFormat pixelFormat, GlTexture::PixelType pixelType, const void* pixeldata)
{
#if defined(GLUE_GL_DEBUG) && defined(GLUE_LOGGING)
    if(!isBound())
        LOG(WARNING) << "Texture2D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage2D(mapTextureType(type()), 0, mapTextureInternalFormat(format), width, height, 0, mapTexturePixelFormat(pixelFormat), mapTexturePixelType(pixelType), pixeldata));
    _format = format;
    _width = width;
    _height = height;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MAX_LEVEL, 0));
}

void GlTexture2D::resize(GlTexture::InternalFormat format, int width, int height)
{
#if defined(GLUE_GL_DEBUG) && defined(GLUE_LOGGING)
    if(!isBound())
        LOG(WARNING) << "Texture2D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage2D(mapTextureType(type()), 0, mapTextureInternalFormat(format), width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0)); // format and type are irrelevant
    _format = format;
    _width = width;
    _height = height;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MAX_LEVEL, 0));
}

int GlTexture2D::width()
{
    return _width;
}

int GlTexture2D::height()
{
    return _height;
}

bool GlTexture2D::isBound() const
{
    GLint currentId = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentId));
    return currentId == (GLint)_id;
}

#ifdef GLUE_LIBPNG
void gltexture2d_png_read_fn(png_structp pngPtr, png_bytep data, png_size_t length)
{
    png_voidp a = png_get_io_ptr(pngPtr);
    ((std::istream*)a)->read((char*)data, length);
}

GlTexture2D* GlTexture2D::fromPNG(std::istream& file)
{
    // from http://www.piko3d.net/tutorials/libpng-tutorial-loading-png-files-from-streams/
    png_byte pngsig[PNGSIGSIZE];

    file.read(reinterpret_cast<char*>(pngsig), PNGSIGSIZE);

    if(!file.good())
        return nullptr;

    if(png_sig_cmp(pngsig, 0, PNGSIGSIZE) != 0)
        return nullptr;

    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!pngPtr)
        return nullptr;

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if(!infoPtr)
    {
        png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
        return nullptr;
    }

    png_set_read_fn(pngPtr,(png_voidp)&file, gltexture2d_png_read_fn);

    png_set_sig_bytes(pngPtr, PNGSIGSIZE);
    png_read_info(pngPtr, infoPtr);

    png_uint_32 width =  png_get_image_width(pngPtr, infoPtr);
    png_uint_32 height = png_get_image_height(pngPtr, infoPtr);
    png_uint_32 bitdepth = png_get_bit_depth(pngPtr, infoPtr);
    png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
    png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngPtr);
        channels = 3;
    }

    png_byte* data = new png_byte[width * height * bitdepth/8 * channels];

    png_bytep* rowPtrs = new png_bytep[height];
    const unsigned int stride = width * bitdepth/8 * channels;

    for (size_t i = 0; i < height; i++)
    {
        png_uint_32 q = (height - i - 1) * stride;
        rowPtrs[i] = (png_bytep)data + q;
    }

    png_read_image(pngPtr, rowPtrs);

    GlTexture2D* tex = new GlTexture2D();
    tex->bind();
    tex->setImageData(GlTexture::InternalFormat::RGBA8, width, height, GlTexture::PixelFormat::RGBA, GlTexture::PixelType::UnsignedByte, data);
    tex->release();

    delete[] data;
    png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);

    return tex;
}
#endif

