#ifndef GLTEXTURE1D_H
#define GLTEXTURE1D_H

#include "glue/GlConfig.h"
#include "glue/GlTexture.h"

/**
 * The GlTexture1D class represents a one dimensional texture.
 */
class GlTexture1D : public GlTexture
{
public:
    /**
     * Creates an empty 1D texture with a width of zero.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenTextures.xhtml">glGenTextures</a>
     */
    GlTexture1D();

    /**
     * Returns Texture1D.
     */
    Type type() const override;

    /**
     * Copies image data to the texture.
     * The pixeldata must have a size of width, a layout in the given format and have the given pixelType.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage1D.xhtml">glTexImage1D</a>
     */
    void setImageData(InternalFormat format, int width, PixelFormat pixelFormat, PixelType pixelType, const void* pixeldata);

    /**
     * Resizes the image to the new format and dimension.
     * This will always clear the current image data even if the size does not change.
     * The actual content of the texture is undefined until explicit data is copied to the texture.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage1D.xhtml">glTexImage1D</a>
     */
    void resize(InternalFormat format, int width);

    /**
     * Returns the width of the texture
     */
    int width();

    bool isBound() const override;

protected:
    int _width;
};

#endif // GLTEXTURE1D_H
