#include "Functionalities/Actions.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>

namespace Controller {

AdminActions intToAdminActions(int action) {
    if (action >= static_cast<int>(AdminActions::ADD_FOOD_ITEM) && 
        action <= static_cast<int>(AdminActions::ADD_ATTRIBUTE)) {
        return static_cast<AdminActions>(action);
    }
    throw std::out_of_range("Invalid AdminActions enum value");
}

ChefActions intToChefActions(int action) {
    if (action >= static_cast<int>(ChefActions::GET_RECOMMENDED_MENU) && 
        action <= static_cast<int>(ChefActions::GET_DISCARDED_FOOD_ITEMS)) {
        return static_cast<ChefActions>(action);
    }
    throw std::out_of_range("Invalid ChefActions enum value");
}

EmployeeActions intToEmployeeActions(int action) {
    if (action >= static_cast<int>(EmployeeActions::VIEW_MENU) && 
        action <= static_cast<int>(EmployeeActions::ADD_DISCARDED_FOOD_ITEM_ANSWER)) {
        return static_cast<EmployeeActions>(action);
    }
    throw std::out_of_range("Invalid EmployeeActions enum value");
}

void writeResponse(std::vector<unsigned char> &buffer, 
                   rapidjson::Document &request, 
                   int statusCode, 
                   rapidjson::Document &payload) {

    if (!payload.IsObject()) {
        payload.SetObject();
    }

    if (payload.HasMember("statusCode")) {
        payload["statusCode"].SetInt(statusCode);
    } else {
        payload.AddMember("statusCode", statusCode, payload.GetAllocator());
    }

    rapidjson::StringBuffer stringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
    payload.Accept(writer);

    const char* responseStr = stringBuffer.GetString();
    buffer.assign(responseStr, responseStr + stringBuffer.GetSize());
}

} // namespace Controller
