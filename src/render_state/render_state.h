
#ifndef __RENDER_STATE_H__
#define __RENDER_STATE_H__

#include "config.h"
#include "shader.h"

namespace skate 
{
    class RenderState
    {
    private:
        RenderState() noexcept {}
        static RenderState instance;

        bool depthTestEnabled;
        GLenum depthFunc;

        bool stencilTestEnabled;
        GLenum stencilFail;
        GLenum depthFail;
        GLenum depthPass;
        GLuint stencilMask;
        GLenum stencilFunc;
        GLint stencilRef;
        GLuint stencilFuncMask;

        bool blendEnabled;
        GLenum blendSource;
        GLenum blendDestination;

        bool faceCullingEnabled;
        GLenum culledFace;
        GLenum frontFaceDirection;

        GLenum polygonMode;

        GLuint activeShaderID;

    public:
        inline static RenderState& Instance(void) noexcept
        {
            return instance;
        }

        void SetDepthTest(bool enable) noexcept;
        void SetDepthFunc(GLenum func) noexcept;

        void SetStencilTest(bool enable) noexcept;
        void SetStencilOptions(GLenum sfail, GLenum dpfail, GLenum dppass) noexcept;
        void SetStencilMask(GLuint mask) noexcept;
        void SetStencilFunc(GLenum func, GLint ref, GLuint mask) noexcept;

        void SetBlend(bool enable) noexcept;
        void SetBlendFunc(GLenum src, GLenum dst) noexcept;
            
        void SetCull(bool enable) noexcept;
        void SetCulledFace(GLenum face) noexcept;
        void SetFrontFaceDirection(GLenum dir) noexcept;
            
        void SetPolygonMode(GLenum mode) noexcept;

        void UseShader(const Shader& shader) noexcept;
    };
}

#endif // __RENDER_STATE_H__
