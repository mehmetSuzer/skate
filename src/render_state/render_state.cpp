
#include "render_state.h"

namespace skate
{
    RenderState RenderState::instance;

    void RenderState::SetDepthTest(bool enable) noexcept
    {
        if (depthTestEnabled != enable)
        {
            depthTestEnabled = enable;
            if (enable)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
        }
    }
    
    void RenderState::SetDepthFunc(GLenum func) noexcept
    {
        if (depthFunc != func)
        {
            depthFunc = func;
            glDepthFunc(func);
        }
    }

    void RenderState::SetStencilTest(bool enable) noexcept
    {
        if (stencilTestEnabled != enable)
        {
            stencilTestEnabled = enable;
            if (enable)
                glEnable(GL_STENCIL_TEST);
            else
                glDisable(GL_STENCIL_TEST);
        }
    }

    void RenderState::SetStencilOptions(GLenum sfail, GLenum dpfail, GLenum dppass) noexcept
    {
        if (stencilFail != sfail || depthFail != dpfail || depthPass != dppass)
        {
            stencilFail = sfail;
            depthFail = dpfail;
            depthPass = dppass;
            glStencilOp(sfail, dpfail, dppass);
        }
    }
            
    void RenderState::SetStencilMask(GLuint mask) noexcept
    {
        if (stencilMask != mask)
        {
            stencilMask = mask;
            glStencilMask(mask);
        }
    }

    void RenderState::SetStencilFunc(GLenum func, GLint ref, GLuint mask) noexcept
    {
        if (stencilFunc != func || stencilRef != ref || stencilFuncMask != mask)
        {
            stencilFunc = func;
            stencilRef = ref;
            stencilFuncMask = mask;
            glStencilFunc(func, ref, mask);
        }
    }

    void RenderState::SetBlend(bool enable) noexcept
    {
        if (blendEnabled != enable)
        {
            blendEnabled = enable;
            if (enable)
                glEnable(GL_BLEND);
            else
                glDisable(GL_BLEND);
        }
    }
            
    void RenderState::SetBlendFunc(GLenum src, GLenum dst) noexcept
    {
        if (blendSource != src || blendDestination != dst)
        {
            blendSource = src;
            blendDestination = dst;
            glBlendFunc(src, dst);
        }
    }
            
    void RenderState::SetCull(bool enable) noexcept
    {
        if (faceCullingEnabled != enable)
        {
            faceCullingEnabled = enable;
            if (enable)
                glEnable(GL_CULL_FACE);
            else
                glDisable(GL_CULL_FACE);
        }
    }
            
    void RenderState::SetCulledFace(GLenum face) noexcept
    {
        if (culledFace != face)
        {
            culledFace = face;
            glCullFace(face);
        }
    }

    void RenderState::SetFrontFaceDirection(GLenum dir) noexcept
    {
        if (frontFaceDirection != dir)
        {
            frontFaceDirection = dir;
            glFrontFace(dir);
        }
    }
            
    void RenderState::SetPolygonMode(GLenum mode) noexcept
    {
        if (polygonMode != mode)
        {
            polygonMode = mode;
            glPolygonMode(GL_FRONT_AND_BACK, mode);
        }
    }
            
    void RenderState::UseShader(const Shader& shader) noexcept
    {
        const GLuint ID = shader.GetID();
        if (activeShaderID != ID)
        {
            activeShaderID = ID;
            glUseProgram(ID);
        }
    }
}
