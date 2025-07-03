use std::ops::{Add, Mul};

//     let t: f64 = 0.5 * direction.y + 1.0;
//     let t_inv = 1.0 - t;
//
//     let my_vec1 = vec3 {
//         x: 1.0 * t_inv,
//         y: 1.0 * t_inv,
//         z: 1.0 * t_inv,
//     };
//     let my_vec2 = vec3 {
//         x: 0.5 * t,
//         y: 0.7 * t,
//         z: 1.0 * t,
//     };
//     let color: vec3 = vec3 {
//         x: my_vec1.x + my_vec2.x,
//         y: my_vec1.y + my_vec2.y,
//         z: my_vec1.z + my_vec2.z,
//     };
//
//     color

#[allow(non_camel_case_types)]
#[derive(Clone, Copy, Debug)]
struct vec3 {
    x: f64,
    y: f64,
    z: f64,
}

impl vec3 {
    fn new(x: f64, y: f64, z: f64) -> Self {
        vec3 { x, y, z }
    }

    fn length(&self) -> f64 {
        (self.x * self.x + self.y * self.y + self.z * self.z).sqrt()
    }

    fn unit_vector(self) -> vec3 {
        let len = self.length();
        vec3::new(self.x / len, self.y / len, self.z / len)
    }
}

fn color(r: Ray) -> vec3 {
    let unit_direction = r.direction.unit_vector();
    let t = 0.5 * (unit_direction.y + 1.0);
    ((1.0 - t) * vec3::new(1.0, 1.0, 1.0)) + (t * vec3::new(0.5, 0.7, 1.0))
}

impl Add for vec3 {
    type Output = vec3;
    fn add(self, rhs: vec3) -> vec3 {
        vec3::new(self.x + rhs.x, self.y + rhs.y, self.z + rhs.z)
    }
}
impl Mul<vec3> for f64 {
    type Output = vec3;
    fn mul(self, v: vec3) -> vec3 {
        vec3::new(self * v.x, self * v.y, self * v.z)
    }
}

#[allow(dead_code)]
#[derive(Copy, Clone, Debug)]
struct Ray {
    origin: vec3,
    direction: vec3,
}

impl Ray {
    fn new(origin: vec3, direction: vec3) -> Self {
        Self { origin, direction }
    }
}

fn main() {
    let nx = 200;
    let ny = 100;
    println!("P3\n{} {}\n255", nx, ny);

    let lower_left_corner = vec3::new(-2.0, -1.0, -1.0);
    let horizontal = vec3::new(4.0, 0.0, 0.0);
    let vertical = vec3::new(0.0, 2.0, 0.0);
    let origin = vec3::new(0.0, 0.0, 0.0);

    for j in (0..ny).rev() {
        for i in 0..nx {
            let u = i as f64 / nx as f64;
            let v = j as f64 / ny as f64;
            let r = Ray::new(
                origin,
                lower_left_corner + ((u * horizontal) + (v * vertical)),
            );
            let col = color(r);
            let ir = (255.99 * col.x) as i32;
            let ig = (255.99 * col.y) as i32;
            let ib = (255.99 * col.z) as i32;
            println!("{} {} {}", ir, ig, ib);
        }
    }
}

// fn main() {
//     let nx = 200;
//     let ny = 100;
//
//     println!("P3\n{} {}\n255", nx, ny);
//
//     for j in 0..ny {
//         for i in 0..nx {
//             let r = i as f32 / nx as f32;
//             let g = (ny - 1 - j) as f32 / ny as f32;
//             let b = 0.2;
//
//             let ir = (255.99 * r) as i32;
//             let ig = (255.99 * g) as i32;
//             let ib = (255.99 * b) as i32;
//
//             println!("{} {} {}", ir, ig, ib);
//         }
//     }
// }

// #[allow(non_camel_case_types)]
// #[derive(Clone, Copy, Debug)]
// struct vec3 {
//     x: f64,
//     y: f64,
//     z: f64,
// }
//
// fn main() {
//     let nx = 200;
//     let ny = 100;
//     println!("P3\n{} {}\n255", nx, ny);
//     let lower_left_corner: vec3 = vec3 {
//         x: -2.0,
//         y: -1.0,
//         z: -1.0,
//     };
//     let horizontal: vec3 = vec3 {
//         x: 4.0,
//         y: 0.0,
//         z: 0.0,
//     };
//     let vertical: vec3 = vec3 {
//         x: 0.0,
//         y: 2.0,
//         z: 0.0,
//     };
//     let origin: vec3 = vec3 {
//         x: 0.0,
//         y: 0.0,
//         z: 0.0,
//     };
//
//     for j in (0..ny).rev() {
//         for i in 0..nx {
//             let u = i as f64 / nx as f64;
//             let v = j as f64 / ny as f64;
//             let new_hor: vec3 = vec3 {
//                 x: u * horizontal.x,
//                 y: u * horizontal.y,
//                 z: u * horizontal.z,
//             };
//             let new_ver: vec3 = vec3 {
//                 x: v * vertical.x,
//                 y: v * vertical.y,
//                 z: v * vertical.z,
//             };
//             let direction_x: f64 = lower_left_corner.x + new_hor.x + new_ver.x;
//             let direction_y: f64 = lower_left_corner.y + new_hor.y + new_ver.y;
//             let direction_z: f64 = lower_left_corner.z + new_hor.z + new_ver.z;
//             let direction: vec3 = vec3 {
//                 x: direction_x,
//                 y: direction_y,
//                 z: direction_z,
//             };
//
//             let color: vec3 = color(origin, direction);
//
//             let ir: i32 = (255.99 * color.x) as i32;
//             let ig: i32 = (255.99 * color.y) as i32;
//             let ib: i32 = (255.99 * color.z) as i32;
//             println!("{ir} {ig} {ib}\n");
//         }
//     }
// }
//
// fn color(_: vec3, direction: vec3) -> vec3 {
//     let t: f64 = 0.5 * direction.y + 1.0;
//     let t_inv = 1.0 - t;
//
//     let my_vec1 = vec3 {
//         x: 1.0 * t_inv,
//         y: 1.0 * t_inv,
//         z: 1.0 * t_inv,
//     };
//     let my_vec2 = vec3 {
//         x: 0.5 * t,
//         y: 0.7 * t,
//         z: 1.0 * t,
//     };
//     let color: vec3 = vec3 {
//         x: my_vec1.x + my_vec2.x,
//         y: my_vec1.y + my_vec2.y,
//         z: my_vec1.z + my_vec2.z,
//     };
//
//     color
// }
