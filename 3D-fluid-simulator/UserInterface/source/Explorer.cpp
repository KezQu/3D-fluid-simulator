#include <Explorer.h>
#include <variant>
#include <ShapeInstance.h>
#include <Object.h>
#include <Particles.h>


Explorer::Explorer(ImVec2 const& size, ImVec2 const& position) 
	:Interface(size, position, ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_AlwaysAutoResize)
{}

void Explorer::Generate() {
	ImGui::SetNextWindowPos(_position);
	ImGui::SetNextWindowSize(_size);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });

	static std::uint64_t selected = 0;
	if (ImGui::Begin("##Explorer", nullptr, _flags)) {
		static std::pair<int, int> objectSelect = { 0,0 };

		ImGui::SetNextItemWidth(_size.x / 3.f);
		ImGui::Combo("##EntityType", &objectSelect.first, " \0Object\0Particle\0");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(_size.x / 3.f);
		ImGui::Combo("##EntityShape", &objectSelect.second, " \0Point\0Line\0Square\0Qube\0Sphere\0");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(_size.x / 3.f);
		if (ImGui::Button("Add Entity##AddEntity") && objectSelect.first != 0 && objectSelect.second != 0) {
			switch (objectSelect.second)
			{
			case 1: 
				objectSelect.first == 1 ? simulatorInstance.Append(Object(new Point())) : simulatorInstance.Append(Particles(new Point(), 1U));
				break;
			case 2:
				objectSelect.first == 1 ? simulatorInstance.Append(Object(new Line())) : simulatorInstance.Append(Particles(new Line(), 1U));
				break;
			case 3:
				objectSelect.first == 1 ? simulatorInstance.Append(Object(new Square())) : simulatorInstance.Append(Particles(new Square(), 1U));
				break;
			case 4:
				objectSelect.first == 1 ? simulatorInstance.Append(Object(new Qube())) : simulatorInstance.Append(Particles(new Qube(), 1U));
				break;
			case 5:
				objectSelect.first == 1 ? simulatorInstance.Append(Object(new Sphere())) : simulatorInstance.Append(Particles(new Sphere(), 1U));
				break;
			}
		}
		if (ImGui::BeginChild("##ObjectExplorer", ImVec2(_size.x, _size.y / 2), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar)) {
			if (ImGui::BeginTable("##NamesTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendY | ImGuiTableFlags_NoHostExtendX, ImVec2(_size.x, _size.y / 2))) {
				ImGui::TableSetupColumn("##Visibilty", ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupColumn("##Name", ImGuiTableColumnFlags_WidthStretch);
				for (auto & [k,v] : simulatorInstance.GetEntities()) {
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Checkbox(("##visible" + std::to_string(v->ID())).c_str(), &v->Visible());
 					ImGui::TableSetColumnIndex(1);
					if (ImGui::Selectable((v->Name() + " ##objectLookup" + std::to_string(v->ID())).c_str())) {
						selected = k;
					}
				}
			}
			ImGui::EndTable();
		}
		ImGui::EndChild();
		if (ImGui::BeginChild("##ObjectDetails", ImVec2(_size.x, _size.y / 2), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar)) {
			if (ImGui::BeginTable("##DetailsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendY | ImGuiTableFlags_NoHostExtendX, ImVec2(_size.x, _size.y / 2)) && selected != 0) {
				ImGui::TableSetupColumn("##InfoName", ImGuiTableColumnFlags_WidthFixed, _size.x / 3.);
				ImGui::TableSetupColumn("##InfoValues", ImGuiTableColumnFlags_WidthStretch);
				
				for (auto& info : simulatorInstance.GetEntities().at(selected)->Details()) {
					ImGui::TableNextRow(); 
					ImGui::TableSetColumnIndex(0);
					ImGui::Text(info.first.c_str());

					ImGui::TableSetColumnIndex(1);
					ImGui::SetNextItemWidth(-1);
					switch (info.second.second)
					{
					case DetailsType::BOOL:
						ImGui::Checkbox(("##" + info.first).c_str(), &std::get<DetailsType::BOOL>(info.second.first)());
						break;
					case DetailsType::STRING:
						ImGui::InputText(("##" + info.first).c_str(), &std::get<DetailsType::STRING>(info.second.first)(), ImGuiInputTextFlags_EnterReturnsTrue);
						break;
					case DetailsType::INT32:
						ImGui::DragInt(("##" + info.first).c_str(), &std::get<DetailsType::INT32>(info.second.first)(), 1, INT_MIN / 2, INT_MAX / 2, "%d", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::UINT64:
						ImGui::DragScalar(("##" + info.first).c_str(), ImGuiDataType_U64, &std::get<DetailsType::UINT64>(info.second.first)(), 1, (void*)0, (void*)0, "%d", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::DISTSHAPE:
						ImGui::DragScalar(("##" + info.first).c_str(), ImGuiDataType_U8, &std::get<DetailsType::DISTSHAPE>(info.second.first)(), 1, (void*)0, (void*)0, "%d", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::FLOAT:
						ImGui::DragFloat(("##" + info.first).c_str(), &std::get<DetailsType::FLOAT>(info.second.first)(), 1.f, -FLT_MAX / 2.f, FLT_MAX / 2.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::VEC2:
						ImGui::DragFloat2(("##" + info.first).c_str(), glm::value_ptr(std::get<DetailsType::VEC2>(info.second.first)()), 1.f, -FLT_MAX / 2.f, FLT_MAX / 2.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::VEC3:
						ImGui::DragFloat3(("##" + info.first).c_str(), glm::value_ptr(std::get<DetailsType::VEC3>(info.second.first)()), 1.f, -FLT_MAX / 2.f, FLT_MAX / 2.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
						break;
					case DetailsType::VEC4:
						ImGui::DragFloat4(("##" + info.first).c_str(), glm::value_ptr(std::get<DetailsType::VEC4>(info.second.first)()), 1.f, -FLT_MAX / 2.f, FLT_MAX / 2.f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
						break;
					default:
						break;
					}
					ImGui::Spacing();
				}
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				if (ImGui::Button("Delete")) {
					simulatorInstance.Delete(selected);
					selected = 0;
				}
				if (ImGui::Button("Recompile")) {
					simulatorInstance.GetEntities()[selected]->Initialize();
				}
			}
			ImGui::EndTable();
		}
		ImGui::EndChild();

	}
	ImGui::End();
	ImGui::PopStyleVar();
}
