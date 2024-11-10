// shadertoy shader fractals
#version 330 core
out vec4 FragColor;

uniform vec2  u_resolution;
uniform float u_time;

float distanceToMandelbrot(in vec2 c) {
#if 1
    {
        float c2 = dot(c, c);
        // skip computation inside M1 - https://iquilezles.org/articles/mset1bulb
        if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.x - 3.0 < 0.0)
            return 0.0;
        // skip computation inside M2 - https://iquilezles.org/articles/mset2bulb
        if (16.0 * (c2 + 2.0 * c.x + 1.0) - 1.0 < 0.0)
            return 0.0;
    }
#endif

    // iterate
    float di = 1.0;
    vec2  z  = vec2(0.0);
    float m2 = 0.0;
    vec2  dz = vec2(0.0);
    for (int i = 0; i < 300; i++) {
        if (m2 > 1024.0) {
            di = 0.0;
            break;
        }

        // Z' -> 2·Z·Z' + 1
        dz = 2.0 * vec2(z.x * dz.x - z.y * dz.y, z.x * dz.y + z.y * dz.x) + vec2(1.0, 0.0);

        // Z -> Z² + c
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;

        m2 = dot(z, z);
    }

    // distance
    // d(c) = |Z|·log|Z|/|Z'|
    float d = 0.5 * sqrt(dot(z, z) / dot(dz, dz)) * log(dot(z, z));
    if (di > 0.5)
        d = 0.0;

    return d;
}

void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 p         = (2.0 * fragCoord - u_resolution) / u_resolution.y;

    // animation
    float tz  = 0.5 - 0.5 * cos(0.225 * u_time);
    float zoo = pow(0.5, 13.0 * tz);
    vec2  c   = vec2(-0.05, .6805) + p * zoo;

    // distance to Mandelbrot
    float d = distanceToMandelbrot(c);

    // do some soft coloring based on distance
    d = clamp(pow(4.0 * d / zoo, 0.2), 0.0, 1.0);

    vec3 col = vec3(d);

    float alpha = d > 0.0 ? 1.0 : 0.0;

    FragColor = vec4(col, alpha);
}
// looks cool but idk

// #version 330 core
// out vec4 FragColor;

// uniform vec2  u_resolution;
// uniform vec2  u_offset;
// uniform float u_zoom;
// uniform int   u_maxIterations;
// uniform float u_time;

// void main() {
//     vec2 c = (gl_FragCoord.xy / u_resolution - vec2(0.5)) * u_zoom * 3.0 + u_offset;
//     vec2 z = vec2(0.0);

//     int   i;
//     float x, y;
//     for (i = 0; i < u_maxIterations; i++) {
//         x = (z.x * z.x - z.y * z.y) + c.x;
//         y = (2.0 * z.x * z.y) + c.y;

//         if ((x * x + y * y) > 4.0)
//             break;

//         z.x = x;
//         z.y = y;
//     }

//     // Smooth coloring
//     float smoothIteration = float(i) - log2(log2(x * x + y * y)) + 4.0;
//     float t               = smoothIteration / float(u_maxIterations);
//     vec3  color           = vec3(t * 0.5, t * 0.3, t * 0.8);

//     // Apply a smooth time-based modulation to the color
//     float timeModulation = 0.5 + 0.5 * sin(u_time * 0.1); // Slow down the time effect
//     color *= timeModulation;

//     FragColor = vec4(color, 1.0);
// }
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
