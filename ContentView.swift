//
//  ContentView.swift
//  ArduiMatorNew
//
//  Created by AnshuDiya on 8/20/26.
//

import SwiftUI

struct ContentView: View {
    @State private var OutputValue = GetDaValue()
    var body: some View {
        
        VStack {
            Image(systemName: "globe")
                .foregroundColor(Color.blue)
                .imageScale(.medium)
            
            Text("Hello, world!")
            Button("Button") {
                CalculatePolynomialCoordsAndPrintAlias("Polynomial", 2.15, 0.23, 1.78, 400.0, 900000.0, 1.0, 310)
            }
            .padding()
            
            .padding()
        }
    }
}
    

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
