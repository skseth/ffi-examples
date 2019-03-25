fn main() {
    println!("cargo:rustc-link-search=target/lib");
    println!("cargo:rustc-link-search=/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server");
    println!("cargo:rustc-link-lib=static=hellocpp");
    println!("cargo:rustc-link-lib=dylib=jvm");
    println!("cargo:rustc-link-lib=dylib=hellogo");
}
