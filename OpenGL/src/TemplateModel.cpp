#include "TemplateModel.h"

TemplateModel::TemplateModel() {}

TemplateModel::~TemplateModel() {}

void TemplateModel::Update(const float& dt) {
    for (int i = 0; i < vertexCount; i += 4) {
        // 获取当前顶点的坐标
        float x = vertexArray[i];
        float y = vertexArray[i + 1];

        // 根据相机的旋转量进行计算和更新
        glm::vec3 rotatedPos = transform.rotation * glm::vec3(x, y, 0.0f);

        // 更新顶点坐标
        vertexArrayTemp[i] = rotatedPos.x;
        vertexArrayTemp[i + 1] = rotatedPos.y;
    }
}
