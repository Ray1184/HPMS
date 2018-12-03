#include <glm/ext.hpp>
#include <string>
#include <iostream>
#include <sstream>
#define GLM_ENABLE_EXPERIMENTAL
#include "../core/Transformation.h"
#include "../core/Window.h"
#include "../core/gl/GLWindow.h"
#include "../core/gl/GLShader.h"
#include "../core/PipelineUtils.h"

/*!
 * File math_test.h
 */
std::string PrintMatrix(glm::mat4& m);

int main()
{
   /* hpms::GLShader shader;*/
    hpms::Options opts;
    hpms::Perspective pers;
    hpms::GLWindow* win = new hpms::GLWindow("Test", 320, 200, true, opts, pers);
    hpms::PipelineUtils::CreateSceneShader();
    //glm::mat4 mat(1.0);
    //new Vector3f(5, 5, 2), new Vector3f(80, 18, 7)
    glm::vec3 pos(10, 5, 20);
    glm::vec3 scal(1, 1, 1);
    glm::quat rot(1, 0.5, 0.1, 0.7);
    hpms::AdvModelItem modelItem;
    modelItem.SetPosition(pos);
    modelItem.SetRotation(rot);
    modelItem.SetScale(scal);
    hpms::Transformation transf;
    transf.BuildModelMatrix(&modelItem);
    //glm::mat4 res = hpms::Transformation::UpdateGenericViewMatrix(transf, rot, mat);
    //std::cout << PrintMatrix(transf.BuildModelMatrix(&modelItem)) << std::endl;
}





std::string PrintMatrix(glm::mat4& m) {
    std::stringstream ss;
    ss << "[" << m[0][0] << "]" << "[" << m[0][1] << "]" << "[" << m[0][2] << "]" << "[" << m[0][3] << "]" << std::endl;
    ss << "[" << m[1][0] << "]" << "[" << m[1][1] << "]" << "[" << m[1][2] << "]" << "[" << m[1][3] << "]" << std::endl;
    ss << "[" << m[2][0] << "]" << "[" << m[2][1] << "]" << "[" << m[2][2] << "]" << "[" << m[2][3] << "]" << std::endl;
    ss << "[" << m[3][0] << "]" << "[" << m[3][1] << "]" << "[" << m[3][2] << "]" << "[" << m[3][3] << "]" << std::endl;
    return ss.str();
}