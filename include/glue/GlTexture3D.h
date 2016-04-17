#ifndef GLTEXTURE3D_H
#define GLTEXTURE3D_H

#include "glue/GlConfig.h"
#include "glue/GlTexture.h"

/**
 * The GlTexture3D class represents a three dimensional texture.
 */
class GlTexture3D : public GlTexture
{
public:
    /**
     * Creates an empty 3D texture with a width, height and depth of zero.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenTextures.xhtml">glGenTextures</a>
     */
    GlTexture3D();

    /**
     * Returns Texture3D
     */
    Type type() const override;

    /**
     * Copies image data to the texture.
     * The pixeldata must have a size of width*height, a layout in the given format and have the given pixelType.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage3D.xhtml">glTexImage3D</a>
     */
    void setImageData(InternalFormat format, int width, int height, int depth, PixelFormat pixelFormat, PixelType pixelType, const void* pixeldata);

    /**
     * Resizes the image to the new format and dimension.
     * This will always clear the current image data even if the size does not change.
     * The actual content of the texture is undefined until explicit data is copied to the texture.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexImage3D.xhtml">glTexImage3D</a>
     */
    void resize(InternalFormat format, int width, int height, int depth);

    /**
     * Returns the width of the texture
     */
    int width();

    /**
     * Returns the height of the texture
     */
    int height();

    /**
     * Returns the depth of the texture
     */
    int depth();

    bool isBound() const override;

protected:
    int _width;
    int _height;
    int _depth;
};

#endif // GLTEXTURE2D_H
