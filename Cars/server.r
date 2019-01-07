palette(c("#E41A1C", "#377EB8", "#4DAF4A", "#984EA3",
          "#FF7F00", "#FFFF33", "#A65628", "#F781BF", "#999999"))

shinyServer(function(input, output, session) {
  load("AudiA4data.Rdata")
  # Combine the selected variables into a new data frame
  selectedData <- reactive({
    AudiA4data[, c(input$xcol, input$ycol)]
  })
  
  observeEvent(input$calc, {
    output$plot1 <- renderPlot({
      par(mar = c(5.1, 4.1, 0, 1))
      plot(selectedData(), col=rgb(1,0,0,0.2), pch = 20, cex = 3)
      lines(sreg(selectedData()[,1], selectedData()[,2])$predicted, lwd = 2, col = "blue")
      best <- which.min((sreg(selectedData()[,1], selectedData()[,2])$residuals))
      points(selectedData()[,1][best],selectedData()[,2][best], pch=16, col="black")
    })
  })
  ?observeEvent()
  
  #clusters <- reactive({
  #kmeans(selectedData(), input$clusters)
  #})
  
  output$plot1 <- renderPlot({
    par(mar = c(5.1, 4.1, 0, 1))
    plot(selectedData(), col=rgb(1,0,0,0.2), pch = 20, cex = 3)
    lines(sreg(selectedData()[,1], selectedData()[,2])$predicted, lwd = 2, col = "blue")
    #points(clusters()$centers, pch = 4, cex = 4, lwd = 4)
  })
  
})