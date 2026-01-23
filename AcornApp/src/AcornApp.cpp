#include "Acorn/Application.h"
#include "Acorn/EntryPoint.h"

#include "Acorn/Image.h"

class ExampleLayer : public Acorn::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Acorn::Application* Acorn::CreateApplication(int argc, char** argv)
{
	Acorn::ApplicationSpecification spec;
	spec.Name = "Acorn Example";

	Acorn::Application* app = new Acorn::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}