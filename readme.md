# **COMP4411**-modeler

Programming project 2 of HKUST Computer Graphics course COMP4411

## Basic Requirements

- [ ] Own character (10 primitive shapes, 4 level of hierarchy)
  - [ ] each level need at least one `glTranslate` `glRotate` or `glScale`
  - [ ] use `glPushMatrix` and `glPopMatrix` to nest the levels
- [ ] Sliders to control single component
- [ ] Sliders to control a action which move multiple components at the same time
- [x] Implement `gluLookAt`
- [ ] Complete 2 bells

## Bonus

B: Bell, W: Whistle, 1B=2W

- [ ] **(1W)** Light source
  - [ ] **(1W)** (hierarchical) level of details
- [ ] **(1B)** Texture map
- [ ] **(1B)** Polygon faces shape
- [ ] **(1B)** Animated sequence
- [ ] (1B) Widget to control param and create individual-looking instances
- [ ] **(1B)** Fit whole model in camera
- [ ] (1B1W) an intuitive way for the user to twist the camera via mouse control.
- [ ] *(2B)* New primitives (is it 2B for each)
  - [ ] 1. Given Curve A and B, surface form by sweep A through B
  - [ ] 2. Given Curve A and stright line L, surface form by rotate A about L
  - [ ] 3. Torus
    4. Others base on coolness
- [ ] (2B) procedural modelling with parameter control [L-system](https://en.wikipedia.org/wiki/L-system)
- [ ] (2B) mood cycling: the model have mood reaction based on UI control
- [ ] (4B) Organic shape [metaballs](http://en.wikipedia.org/wiki/Metaballs)
- [ ] *(8B)* goal-oriented motion (inverse kinematics  [here](https://course.cse.ust.hk/comp4411/Password_Only/projects/modeler/inverse-kinematics.pdf))
  - [ ] *(4B)* constrain on joints
