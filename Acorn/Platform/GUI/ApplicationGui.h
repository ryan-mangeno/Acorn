#include <unistd.h>
#include <functional>

#include "Core/Util/Util.h" 
#include "Core/Layer.h"
#include "Core/TimeStep.h"

GLFWwindow;
namespace Acorn {

    class Application
    {
        public:
            struct Specification
            {
                Specification(uint32_t width = 1280, uint32_t height = 720, const std::string& name)
                    : Width(width), Height(height), Name(name)
                {}
                
                uint32_t Width;
                uint32_t Height;
                std::string Name = "Acorn App";
            };

        public:
            inline static Application& Get() 
            {
                static Application app;
                return app;
            }

            ~Application();

            void SetMenuBarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

            inline Specification& GetSpecification() { return m_Specification; }

            void Init();
            void Run();
            void Close();

            template<typename T>
            void PushLayer(const Ref<T>& layer) 
            {
                static_assert(std::is_base_of<Layer, T>::value, "Tried to push layer that didn't derive Layer Class!");
                m_LayerStack.emplace_back(layer);
                layer->OnAttach();
            }
            

        private:
            Application();
            Application(const Specification& spec) : m_Specification(spec) {}

        private:
            Specification m_Specification;
            Function<void> m_MenubarCallback;

            float m_PrevFrame;
            TimeStep m_TimeStep;

            GLFWwindow* m_Window; // temporary for now, will abstract windows widow, mac ...
            std::vector<Ref<Layer>> m_LayerStack;
    }; 

    Application* CreateApplication(int argc, char** argv);
}