# MK_Engine
The aim of this project was to create a user-friendly physics engine based on the SFML library.

# Calculating collision response 
Engine uses widely known formula to calculate collision impulse (that is the collision force with is later applied to colliding objects):
<p align="center">
  <img  src="https://github.com/michal34512/MK_Engine/assets/136522993/aa4bd5a5-adce-44b0-8443-06883424a9c9">
</p>
<b>e</b> - greater of the two coefficients of restitution</br>
<b>V<sup>AB</sup></b> - the difference between velocities of the objects at the point of collision</br>
<b>mass<sup>A</sup>, mass<sup>B</sup></b> - objects masses</br>
<b>I<sup>A</sup>, I<sup>B</sup></b> - moments of inertia</br>
<b>r<sup>A</sup>, r<sup>B</sup></b> - vectors from the centers of the objects to the point of collision</br>
<b>t</b> - collision normal</br>
<p align="center">
  <img  src="https://github.com/michal34512/MK_Engine/assets/136522993/afdc1bd5-5851-4aff-b529-89db5ee0d57a">
</p>
<p align="center">
  Next the collision impulse is being applied to both objects according to the equations:
  <img  src="https://github.com/michal34512/MK_Engine/assets/136522993/6d2f2177-8c9c-4851-9e69-b0a010282141">
</p>
