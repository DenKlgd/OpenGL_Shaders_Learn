#version 330

in vec3 localCoords;
in vec4 worldCoords;
uniform float time;

vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

void main()
{
    vec2 coords = localCoords.xy;
    vec3 color;

    for (int i = 0; i < 4; i++)
    {
        coords = fract(coords * 1.5) - 0.5;
        float d = length(coords.xy) * exp(-length(localCoords.xy));
        vec3 col = palette(length(localCoords.xy) + i * .4 + time * .4);

        d = sin(d * 8 + time) / 8;
        d = abs(d);

        d= pow(0.01 / d, 1.2);

        color += col * d;
    }

    gl_FragColor = vec4(color, 1.0);
    //gl_FragColor = vec4(d, 0, 0, 1.0);
}
