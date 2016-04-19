#ifndef GLQUERY_H
#define GLQUERY_H

#include "glue/GlConfig.h"
#include <cstdint>

/**
 * The GlQuery class represents a OpenGL Query object.
 * A query can retrieve certain information from the GPU.
 * Currently only supports querying the elapsed times.
 *
 * Example:
 * \code
 * GlQuery q(GlQuery::Target::TimeElapsed);
 * q.begin();
 * // .. code that should be measured ..
 * q.end();
 * auto elapsed = q.retrieve();
 * \endcode
 */
class GlQuery
{
public:
    /// Type of the query
    enum class Target
    {
        TimeElapsed
    };

    /**
     * Creates a new query object.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenQueries.xhtml">glGenQueries</a>
     */
    GlQuery(Target target);

    /**
      * Deletes the query object
      * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteQueries.xhtml">glDeleteQueries</a>
      */
    ~GlQuery();

    /**
     * Starts the query.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBeginQuery.xhtml">glBeginQuery</a>
     */
    void begin();
    /**
     * Ends the query.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glEndQuery.xhtml">glEndQuery</a>
     */
    void end();

    /**
     * Retrieves the value of the previous active query.
     * This blocks until the query result is available.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetQueryObjectuiv.xhtml">glGetQueryObjectuiv</a>
     */
    uint32_t retrieve();

    /**
     * Retrieves the value of the previous active query.
     * This blocks until the query result is available.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetQueryObjectui64v.xhtml">glGetQueryObjectui64v</a>
     */
    uint64_t retrieve64();

private:
    const Target _target;
    unsigned int _id;
};

#endif // GLQUERY_H
