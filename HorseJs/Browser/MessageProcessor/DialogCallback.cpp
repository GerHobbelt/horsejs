#include "DialogCallback.h"
void DialogCallback::OnFileDialogDismissed(const std::vector<CefString>& file_paths)
{
	json result;
	result["success"] = true;
	result["data"] = {};
	for (size_t i = 0; i < file_paths.size(); i++)
	{
		result["data"].push_back(file_paths[i].ToString());
	}
}