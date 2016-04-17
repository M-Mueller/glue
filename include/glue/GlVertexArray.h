#ifndef GLVERTEXARRAY_H
#define GLVERTEXARRAY_H

#include "glue/GlConfig.h"
#include "glue/GlVertexBuffer.h"
#include "glue/GlIndexBuffer.h"

/**
 * The GlVertexArray class stores all states required to draw vertex data.
 * A vertex array object (VAO) structures the data from a GlVertexBuffer and optionally orders them with an GlIndexBuffer.
 * Attributes for each vertex will be passed to the vertex shader in the order the are defined in the GlVertexBuffer.
 * For example the first data vector passed to the GlVertexBuffer will be available at the first input location in the shader.
 *
 * The vertex array is has to be \ref bind "bound" before can be modified.
 *
 * \code
 * GlVertexBuffer* vbo = ...
 * GlVertexArray* vao = new GlVertexArray;
 * vao->bind();
 * vao->setVertexData(vbo);
 * vao->unbind();
 * vbo->release(); // was implicitly bound by setVertexData
 * \endcode
 */
class GlVertexArray
{
public:
    /// Rendering primitives
    enum class Primitive
	{
        Points,
        LineStrip,
        LineLoop,
        Lines,
        TriangleStrip,
        TriangleFan,
        Triangles
	};

    /**
     * Creates an empty vertex array.
     * If autoEnableAttributes is true, all attributes found in a vertex buffer are automatically enabled.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenVertexArrays.xhtml">glGenVertexArrays</a>
     */
    GlVertexArray(bool autoEnableAttributes=true);

    /**
     * Deletes the vertex array.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteVertexArrays.xhtml">glDeleteVertexArrays</a>
     */
	virtual ~GlVertexArray();

    /**
     * Binds the vertex array.
     * Unbinds any previously bound vertex arrays.
     * Be aware that OpenGL implicitly unbinds buffers bound to ElementArray.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindVertexArray.xhtml">glBindVertexArray</a>
     */
	virtual void bind();

    /**
     * Unbinds all vertex arrays.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindVertexArray.xhtml">glBindVertexArray</a>
     */
	virtual void release();

    /**
     * Returns true if this vertex buffer is currently bound.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGet.xhtml">glGet</a>
     */
    virtual bool isBound() const;

    /**
     * Sets the vertex data of the vertex array.
     * The VBO gets automatically bound and must remain bound until the VAO is released.
     * The VBO is NOT released automatically after the VAO is released!
     * After setting the VBO, it must remain valid as long as the VAO is valid.
     *
     * If autoEnableAttributes was set to true, all attributes of the GlVertexBuffer are enabled.
     * Otherwise they stay in their previous state (disabled by default).
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glVertexAttribPointer.xhtml">glVertexAttribPointer</a>
     */
    virtual void setVertexData(GlVertexBuffer &vbo);

    /**
     * Sets an optional index buffer.
     * The IBO gets automatically bound and must remain bound until the VAO is released.
     * The IBO is NOT released automatically after the VAO is released!
     * After setting the IBO, it must remain valid as long as the VAO is valid.
     */
    virtual void setIndexBuffer(GlIndexBuffer &ibo);

    /**
     * Draws the primitves of the vertex buffer directly without an index buffer.
     * The mode usually depends on the content of the vertex buffer, e.g. rendering Lines as Triangles will probably result in artifacts.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDrawArrays.xhtml">glDrawArrays</a>
     */
	virtual void draw(Primitive mode);

    /**
     * Draws primitives by retrieving vertex data according to the index buffer.
     * An index buffer must be set in advance otherwise nothing is drawn.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDrawElements.xhtml">glDrawElements</a>
     */
    virtual void drawElements(Primitive mode);

    /**
     * Enables the attribute with the given index.
     * The index of each attribute is determined by the order in the GlVertexBuffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glEnableVertexAttribArray.xhtml">glEnableVertexAttribArray</a>
     */
	void enableAttribute(unsigned int index);

    /**
     * Disables the attribute with the given index.
     * The index of each attribute is determined by the order in the GlVertexBuffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDisableVertexAttribArray.xhtml">glDisableVertexAttribArray</a>
     */
	void disableAttribute(unsigned int index);

private:
    unsigned int _id;
    bool _autoEnableAttributes;
	size_t _numVertices;
    size_t _numIndices;
    GlIndexBuffer::IndexType _indexType;
};

#endif // GLVERTEXARRAY_H
