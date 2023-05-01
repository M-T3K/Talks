import excepciones.ExcepcionAritmeticaPropia;

public class MainExceptions {
	public static int dividir(String numeradorString, String denominadorString) throws ExcepcionAritmeticaPropia, NumberFormatException {
        
		int numerador = Integer.parseInt(numeradorString); // NumberFormatException
        int denominador = Integer.parseInt(denominadorString); // NumberFormatException
		
		if (denominador == 0) {
            throw new ExcepcionAritmeticaPropia("División por cero no está permitida");
        }
        return numerador / denominador;
    }

    public static void nivel2(String numeradorString, String denominadorString) throws ExcepcionAritmeticaPropia, NumberFormatException {
        int resultado = dividir(numeradorString, denominadorString);
        System.out.println("Resultado: " + resultado);
    }

    public static void nivel1(String numeradorString, String denominadorString) throws ExcepcionAritmeticaPropia, NumberFormatException {
        nivel2(numeradorString, denominadorString);
    }
    
    //==============================================
    // 			COMO ODIO LAS EXCEPCIONES
    //==============================================
    
    public static int dividir(int numerador, int denominador) throws ExcepcionAritmeticaPropia {
        
		if (denominador == 0) {
            throw new ExcepcionAritmeticaPropia("División por cero no está permitida");
        }
        return numerador / denominador;
    }

    public static void nivelIntermedio(String numeradorString, String denominadorString) throws ExcepcionAritmeticaPropia, NumberFormatException {
        
//    	La Excepcion es automatica: esta comprendida en parseInt
//    	int java.lang.Integer.parseInt(String s) throws NumberFormatException
    	int numerador = Integer.parseInt(numeradorString);
        int denominador = Integer.parseInt(denominadorString);
        
    	int resultado = dividir(numerador, denominador);
        System.out.println("Resultado: " + resultado);
        
//        Podrias hacer el TryCatch dentro de este metodo si quieres, 
//        asi no lo harias en el main
    }

    public static void main(String[] args) {
    	
    	System.out.println("PRIMER EJEMPLO");
    	
        try {
            nivel1("10", "0");
        } catch (ExcepcionAritmeticaPropia e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Operación finalizada");
        }
        
        System.out.println("SEGUNDO EJEMPLO");
    	
        try {
            nivelIntermedio("10", "0");
        } catch (ExcepcionAritmeticaPropia e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Operación finalizada");
        }
        
    }
}
