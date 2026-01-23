#include "Input.h"

#include <glfw3.h>
namespace Acorn {

    bool Acorn::IsKeyDown(KeyCode keycode) 
    {
        // need to make application ctx to get window 
        // GLFW* window = Application::GetWindow();
        //return glfwGetKey(/*window*/, keycode) == GLFW_PRESS;
        return false;
    }

    bool Acorn::IsMouseButtonDown(MouseButton button) 
    {
        return false;
    }
    
    glm::vec2 Acorn::GetMousePosition() 
    {
        return {0.f, 0.f};
    }
    
    void Acorn::SetCursorMode(CursorMode mode) 
    {
    
    }


}