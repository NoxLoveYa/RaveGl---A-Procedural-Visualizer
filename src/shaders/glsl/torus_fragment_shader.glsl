// #version 330 core
// out vec4 FragColor;
// in vec2 TexCoord;
// in vec3 FragPos;
// in vec3 Normal;
// uniform sampler2D texture1;
// uniform vec3 lightPos;
// uniform vec3 viewPos;
// uniform vec3 lightColor;
// uniform vec3 objectColor;

// void main()
// {
//     // Ambient lighting
//     float ambientStrength = 0.1;
//     vec3 ambient = ambientStrength * lightColor;
    
//     // Diffuse lighting
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(lightPos - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * lightColor;
    
//     // Specular lighting
//     float specularStrength = 0.5;
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
//     vec3 specular = specularStrength * spec * lightColor;
    
//     // Combine results
//     vec3 result = (ambient + diffuse + specular) * objectColor;
    
//     // Debug output
//     if (length(ambient) < 0.1) {
//         result = vec3(1.0, 0.0, 0.0); // Red color for debugging ambient
//     } else if (length(diffuse) < 0.1) {
//         result = vec3(0.0, 1.0, 0.0); // Green color for debugging diffuse
//     } else if (length(specular) < 0.1) {
//         result = vec3(0.0, 0.0, 1.0); // Blue color for debugging specular
//     }
    
//     FragColor = vec4(result, 1.0); // Remove texture influence for debugging
// }
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Debug output for ambient lighting
    vec3 result = ambient * objectColor;
    if (length(result) < 0.1) {
        result = vec3(1.0, 0.0, 0.0); // Red color for debugging ambient
    } else {
        result = vec3(0.0, 1.0, 0.0); // Green color if ambient is correct
    }
    
    FragColor = vec4(result, 1.0); // Remove texture influence for debugging
}