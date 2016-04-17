#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "glue/GlConfig.h"

/**
 * @brief The GlTexture class is the abstract base class of all texture types.
 */
class GlTexture
{
public:
    /// Texture types
    enum class Type
    {
        Texture1D,
        Texture2D,
        Texture3D
    };

    /// Possible formats of the image in the GPU memory
    enum class InternalFormat
    {
        Invalid,
        R8,
        RG8,
        RGB8,
        RGBA8,
        R16,
        RG16,
        RGB16,
        RGBA16,
        R16F,
        RG16F,
        RGB16F,
        RGBA16F,
        R32F,
        RG32F,
        RGB32F,
        RGBA32F,
        DepthComponent16,
        DepthComponent24,
        DepthComponent32,
        DepthComponent32F
    };

    /// Format of an input image
    enum class PixelFormat
    {
        Red,
        RG,
        RGB,
        RGBA,
        BGR,
        BGRA
    };

    /// Type of an input image
    enum class PixelType
    {
        UnsignedByte,
        Byte,
        UnsignedShort,
        Short,
        HalfFloat,
        Float
    };

    /// Minification filters
    enum class MinFilter
    {
        Nearest,
        Linear,
        NearestMipMapNearest,
        LinearMipMapNearest,
        NearestMipMapLinear,
        LinearMipMapLinear
    };

    /// Magnification filters
    enum class MagFilter
    {
        Nearest,
        Linear
    };

    /// Wrapping options
    enum class Wrap
    {
        ClampToEdge,
        ClampToBorder,
        GlMirroredRepeat,
        Repeat,
        MirrorClampToEdge
    };

    /**
     * Creates a new, empty texture.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenTextures.xhtml">glGenTextures</a>
     */
    GlTexture();

    /**
     * Deletes the texture.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteTextures.xhtml">glDeleteTextures</a>
     */
    virtual ~GlTexture();

    /// Returns the internal OpenGL name of the texture.
    unsigned int id() const;

    /**
     * Returns the type of the texture.
     * Each subclass will represent one type.
     */
    virtual Type type() const =0;

    /**
     * Returns the texture format on the GPU.
     * If no image has been loaded yet or the loading failed, the format will be Invalid.
     */
    virtual InternalFormat format() const;

    /**
     * Returns true if the current InternalFormat is one of the DepthComponent formats.
     */
    virtual bool hasDepthFormat() const;

    /**
     * Binds the texture to a texture unit.
     * If unit is non-negative, the active texture will be changed and the texture bound to that unit.
     * Otherwise the texture is bound to the currently active unit (the unit is not changed).
     * The texture unit is not reset automatically to the previous active unit!
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindTexture.xhtml">glBindTexture</a>
     */
    virtual void bind(int unit=-1);

    /**
     * Unbinds the texture from a unit.
     * If called with a non-negative unit, the active unit will be changed before unbinding.
     * Otherwise the texture of the currently active unit is unbound (which is not necessarely the unit the texture was bound to).
     * The texture unit is not reset automatically to the previous active unit!
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindTexture.xhtml">glBindTexture</a>
     */
    virtual void release(int unit=-1);

    /**
     * Returns true if the texture is currently bound.
     * This method does not change the active texture, i.e. it checks if the texture is bound to the currently active unit.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGet.xhtml">glGet</a>
     */
    virtual bool isBound() const =0;

    /**
     * Sets the minifying function.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexParameter.xhtml">glTexParameter</a>
     */
    void setMinFilter(MinFilter filter);

    /**
     * Sets the magnification function.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glTexParameter.xhtml">glTexParameter</a>
     */
    void setMagFilter(MagFilter filter);

protected:
    unsigned int _id;
    InternalFormat _format;
};

#endif // GLTEXTURE_H
