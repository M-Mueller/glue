#ifndef GLTEXTURE2D_H
#define GLTEXTURE2D_H

#include "glue/GlConfig.h"
#include "glue/GlTexture.h"
#include <fstream>

/**
 * The GlTexture2D class represents a two dimensional texture.
 */
class GlTexture2D : public GlTexture
{
public:
    /**
     * Creates an empty 2D texture with a width and height of zero.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenTextures.xhtml">glGenTextures</a>
     */
    GlTexture2D();

#ifdef GLUE_LIBPNG
    /**
     * Creates a new texture from a png file.
     * The given file stream must be opened in advanced.
     * If the file could not be loaded, 0 is returned.
     */
    static GlTexture2D* fromPNG(std::istream& file);
#endif

    /**
     * Returns Texture2D
     */
    Type type() const override;

    /**
     * Copies image data to the texture.
     * The pixeldata must have a size of width*height, a layout in the given format and have the given pixelType.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml">glTexImage2D</a>
     */
    void setImageData(InternalFormat format, int width, int height, PixelFormat pixelFormat, PixelType pixelType, const void* pixeldata);

    /**
     * Resizes the image to the new format and dimension.
     * This will always clear the current image data even if the size does not change.
     * The actual content of the texture is undefined until explicit data is copied to the texture.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml">glTexImage2D</a>
     */
    void resize(InternalFormat format, int width, int height);

    /**
     * Returns the width of the texture
     */
    int width();

    /**
     * Returns the height of the texture
     */
    int height();

    bool isBound() const override;

protected:
    int _width;
    int _height;
};

#endif // GLTEXTURE2D_H
