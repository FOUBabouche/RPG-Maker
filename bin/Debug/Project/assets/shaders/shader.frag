uniform vec2 iResolution;
uniform float iTime;


void mainImage( out vec4 fragColor, in vec2 fragCoord ){
	float t = iTime;
	vec2 r = iResolution;
	vec3 c;
	float l,z=t;
	for(int i=0;i<3;i++) {
		vec2 uv,p=fragCoord.xy/r;
		uv=p;
		p-=.5;
		p.x*=r.x/r.y;
		z+=.07;
		l=length(p);
		uv+=p/l*(sin(z)+1.)*abs(sin(l-z-z));
		c[i]=.01/length(mod(uv,1.)-.5);
	}
	fragColor=vec4(c/l,t);
}

void main()
{
    vec4 color;
    mainImage(color, gl_FragCoord.xy);
    gl_FragColor = color;
}