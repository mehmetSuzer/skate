
#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "transform.h"
#include "shader.h"

namespace skate
{
    class Renderable
    {
    private:
        bool selected = false;

    public:
        Transform transform;

        inline bool IsSelected(void) const noexcept
        {
            return selected;
        }

        inline void Select(void) noexcept
        {
            selected = true;
        }

        inline void Unselect(void) noexcept
        {
            selected = false;
        }
        
        virtual void Render(const Shader& shader) const noexcept = 0;
        virtual void Delete(void) const noexcept = 0;
    };
}

#endif // __RENDERABLE_H__
