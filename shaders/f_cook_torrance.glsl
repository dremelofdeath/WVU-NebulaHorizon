uniform float refraction;
uniform float slopes;
varying vec3 normal;
varying vec3 position;

float CookTorranceSpecularLocalViewer(vec3 n, vec3 l);
float CookTorranceSpecularInfiniteViewer(vec3 n, vec3 l);

void main(void) {
   vec3 l = normalize(gl_LightSource[0].position.xyz); //eye-space light vector 
   vec3 n = normalize(normal);              //eye-space normal vector
   
   vec4 diffuse = gl_LightSource[0].diffuse*(max(0.0, dot(n, l)));
   diffuse *= gl_FrontMaterial.diffuse;
   
   float Rs = CookTorranceSpecularLocalViewer(n,l);
   
   vec4 specular = gl_LightSource[0].specular*Rs;
   specular *= gl_FrontMaterial.specular;

   vec4 ambient = gl_LightModel.ambient * gl_LightSource[0].ambient;
   ambient *= gl_FrontMaterial.ambient;

   gl_FragColor = ambient + diffuse + specular;
}

float CookTorranceSpecular(vec3 n, vec3 l, vec3 r, vec3 v) {
   vec3 h = normalize(l+v);
   float dotnr = dot(n, r);
   float dotnv = dot(n, v);
   float dotnl = dot(n, l);
   float dotnh = dot(n, h);
   float c = dot(v, h);
   float g = max(0.0, sqrt(pow(refraction, 2.0)+pow(c, 2.0)-1.0));
   float f1 = pow(g-c, 2.0)/(0.0000001+(2.0*pow(g+c, 2.0)));
   float f2top = c*(g+c)-1.0;
   float f2bot = c*(g-c)+1.0;
   float f2 = (1.0+f2top*f2top/(f2bot*f2bot));
   float f = f1*f2;
   float alpha = acos(dotnh);
   float d1 = exp(-1.0*pow(tan(alpha)/slopes, 2.0));
   float d2 = 4.0*pow(slopes, 2.0)*pow(cos(alpha), 4.0);
   float d = d1/d2;
   float gfactor = 2.0*dotnh/(0.000001+c);
   float gmasking = gfactor*dotnv;
   float gshadowing = gfactor*dotnl;
   float ga = max(0.0, min(1.0, min(gmasking, gshadowing)));
   return f*d*ga/(3.1415926535*dotnv*dotnl);
}

float CookTorranceSpecularLocalViewer(vec3 n, vec3 l) {
   vec3 r = reflect(-l, n);
   vec3 v = normalize(-position);
   //vec3 r = normalize(l+v);
   return CookTorranceSpecular(n, l, r, v);
}

float CookTorranceSpecularInfiniteViewer(vec3 n, vec3 l) {
   vec3 r = reflect(-l, n);
   vec3 v = vec3(0.0, 0.0, 1.0);
   return CookTorranceSpecular(n, l, r, v);
}
