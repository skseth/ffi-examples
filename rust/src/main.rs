
// c++
type EncryptFn = extern "C" fn(*const u8, isize);

extern "C" {
    fn initialize_java_callback(encryptfn: EncryptFn) -> i32;
    fn invokeJavaEncrypt();
    fn invokeJavaMain();
}

extern "C" fn do_encrypt(buf: *const u8, length: isize ) {
    println!("  encrypt in rust");

    for i in 0..length {
        println!("    Buf value {}", unsafe {*(buf.offset(i))});
    }
}

// golang
extern "C" {
    fn invokeGoEncrypt();
}


fn main() {
    let i = unsafe { initialize_java_callback(do_encrypt) };
    if i != 0 {
        println!("Error - Initialize java is {}", i);
    } else {
        println!("Finished Initialization of java");
    }

    // invoke java main
    unsafe { invokeJavaMain(); }
    println!("Finished Java Main");

    // invoke encrypt function directly
    println!("Invoking encrypt from rust->cpp->java->cpp->rust");
    unsafe { invokeJavaEncrypt(); }
    println!("Finished java encrypt");

    println!("Invoking go encrypt");
    unsafe { invokeGoEncrypt() }
    println!("Finished go encrypt");
}