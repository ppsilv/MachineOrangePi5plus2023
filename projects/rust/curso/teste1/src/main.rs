use std::io;
 
fn convert_to_int(data_input: &String) -> i32{
    let x= data_input.trim().parse().unwrap();
    x
}
 
fn main() {
    let mut number1 = String::new();
    io::stdin().read_line(&mut number1).expect("Erro ao ler number1");
    let mut number2 = String::new();
    io::stdin().read_line(&mut number2).expect("Erro ao ler number2");
 
    println!("numero1 {} numero2 {}", number1, number2);
    


    if convert_to_int(&number1) > convert_to_int(&number2){
        println!("O numero {} eh maior que {}", number1, number2);
    } else{
        println!("O numero {} eh menor ou igual que {}", number1, number2);
 
    }
}
/*

fn main() {
    println!("Teste de atribuição de valores a uma variável!");

    let name = "Carla";
    let mut valor = 0;

    println!("Nome {name}");

    let mut _i: i32;

    for _i  in 1..128{
        valor+=_i;
        println!("Valor = {}",valor)
    }

}
*/