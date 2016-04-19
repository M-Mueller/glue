#include "glue/GlQuery.h"
#include "glue/GlInternal.h"

GlQuery::GlQuery(GlQuery::Target target):
    _target(target),
    _id(0)
{
    GL_SAFE_CALL(glGenQueries(1, &_id));
}

GlQuery::~GlQuery()
{
    GL_SAFE_CALL(glDeleteQueries(1, &_id));
}

void GlQuery::begin()
{
    GL_SAFE_CALL(glBeginQuery(mapQueryTarget[_target], _id));
}

void GlQuery::end()
{
    GL_SAFE_CALL(glEndQuery(mapQueryTarget[_target]));
}

uint32_t GlQuery::retrieve()
{
    uint32_t param;
    GL_SAFE_CALL(glGetQueryObjectuiv(_id, GL_QUERY_RESULT, &param));
    return param;
}

uint64_t GlQuery::retrieve64()
{
    uint64_t param;
    GL_SAFE_CALL(glGetQueryObjectui64v(_id, GL_QUERY_RESULT, &param));
    return param;
}
