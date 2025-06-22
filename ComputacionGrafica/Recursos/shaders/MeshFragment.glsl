#version 330 core
out vec4 FragColor;

in vec3 ourColor;   // El color del objeto
in vec2 texCoord;   // Coordenadas de textura
in vec3 normal;     // El normal del fragmento
in vec3 wposition;   // La posici�n del fragmento en el espacio
in vec3 pixelToCam;

uniform sampler2D tex0;       // Textura del objeto
uniform float shininess;      // Brillo para la reflexi�n especular


struct Light{
vec3 position;
vec4 color;
float ambientIntensity;
float diffuseIntensity;
};

uniform Light lights[10];

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(pixelToCam - wposition);
    vec3 result = vec3(0.0);


    for (int i = 0; i < 2; i++) {
        vec3 lightDir = normalize(lights[i].position - wposition); // Direcci�n de la luz
        vec3 reflectDir = reflect(-lightDir, norm);   // Direcci�n de la reflexi�n

        
        vec3 ambient = lights[i].ambientIntensity * lights[i].color.rgb;
     


        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lights[i].color.rgb * lights[i].diffuseIntensity;
  

        vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0f), shininess) * lights[i].color.rgb * lights[i].diffuseIntensity;


        result += (ambient + diffuse + specular);


   
    }


    result *= vec3(texture(tex0, texCoord));

    FragColor = vec4(result, 1.0f);
    

}
