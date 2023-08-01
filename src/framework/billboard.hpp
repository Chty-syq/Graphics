//
// Created by syq on 23-7-28.
//

#pragma once

class Billboard {
private:
    std::string texture;
    GLuint vao{}, vbo{};

    const int rows = 10;
    const int cols = 10;
public:
    explicit Billboard(const std::string& texture);
    ~Billboard();
    void Render(shared_ptr<Shader>& shader);
};


Billboard::Billboard(const std::string& texture) {
    this->texture = texture;

    vector<glm::vec3> positions;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            positions.emplace_back(j, 0.0f, i);
        }
    }
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Billboard::~Billboard() {
    glDeleteBuffers(1, &vbo);
}

void Billboard::Render(shared_ptr<Shader> &shader) {
    shader->Use();
    ResourceManager::BindTexture(this->texture, 0);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_POINTS, 0, rows * cols);
    glBindVertexArray(0);
}
