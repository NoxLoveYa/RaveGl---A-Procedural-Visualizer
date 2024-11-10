#version 330 core
out vec4 FragColor;

uniform vec2  u_resolution;
uniform vec2  u_offset;
uniform float u_zoom;
uniform int   u_maxIterations;
uniform float u_time;

void main() {
    vec2 c = (gl_FragCoord.xy / u_resolution - vec2(0.5)) * u_zoom * 3.0 + u_offset;
    vec2 z = vec2(0.0);

    int   i;
    float x, y;
    for (i = 0; i < u_maxIterations; i++) {
        x = (z.x * z.x - z.y * z.y) + c.x;
        y = (2.0 * z.x * z.y) + c.y;

        if ((x * x + y * y) > 4.0)
            break;

        z.x = x;
        z.y = y;
    }

    // Smooth coloring
    float smoothIteration = float(i) - log2(log2(x * x + y * y)) + 4.0;
    float t               = smoothIteration / float(u_maxIterations);
    vec3  color = vec3(t * 0.5, t * 0.3, t * 0.8) * abs(sin(u_time)); // Use time for animation
    FragColor   = vec4(color, 1.0);
}
// #version 330 core
// out vec4 FragColor;

// uniform vec2  u_resolution;
// uniform vec2  u_offset;
// uniform float u_zoom;
// uniform int   u_maxIterations;
// uniform float u_time;

// void main() {
//     vec2 c          = (gl_FragCoord.xy / u_resolution - vec2(0.5)) * u_zoom * 3.0 + u_offset;
//     vec2 z          = vec2(0.0);
//     int  iterations = 0;
//     for (int i = 0; i < u_maxIterations; i++) {
//         vec2 z_new;
//         z_new.x = z.x * z.x - z.y * z.y + c.x;
//         z_new.y = 2.0 * z.x * z.y + c.y;
//         z       = z_new;

//         if (dot(z, z) > 4.0) {
//             iterations = i;
//             break;
//         }
//     }

//     float t     = float(iterations) / float(u_maxIterations);
//     vec3  color = vec3(t, t * 0.5, t * 0.8);
//     FragColor   = vec4(color, 1.0);
// }
